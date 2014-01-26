var child_process = require('child_process');
var exec = child_process.exec;
var spawn = child_process.spawn;
var SerialPort = require("serialport").SerialPort;

exec('make test', {}, function(error, stdout, stderr) {
  console.log('make stdout: ' + stdout);
  console.log('make stderr: ' + stderr);
  if (error !== null) {
    console.log('make exec error: ' + error);
    return;
  }

  var simduino_data = '';
  var env = process.env;

  // enable the serial port to collect results
  env['SIMAVR_UART_TAP'] = '1';

  // disable picocom and xterm so that we can connect to the serial port
  env['SIMAVR_UART_XTERM'] = '0';

  // TODO: The build path for simduino is
  // likely specific to my vagrant environment
  // and as such needs to be parameterized
  var simduino = spawn('./obj-x86_64-linux-gnu/simduino.elf', [], {
    cwd: env['SIMAVR_HOME'] + '/examples/board_simduino',
    env: env
  });

  simduino.stderr.on('data', function (data) {
    console.log('simduino stderr: ' + data);
    simduino_data += data;

    // TODO: The OpenGL stuff in simduino seems to break the stdout here so that it no longer comes out. As such
    // the only output I get is the initial 'unsupported check type 03' stuff on stderr. It would be nice if I could get
    // the other output that goes to the terminal when I launch simduino at the command line as this includes
    // the actual port used so I could stop hardcoding it (it does change under certain conditions - eg. another
    // instance running)
    //
    // if (simduino_data.indexOf('note: export SIMAVR_UART_XTERM=1 and install picocom to get a terminal') !== -1) {
    if (simduino_data.indexOf('read_ihex_file: ATmegaBOOT_168_atmega328.ihex, unsupported check type 03') !== -1) {
      // var regex = /uart_pty_init tap on port \*\*\* ([^\s]*) \*\*\*/g
      // var match = regex.exec(simduino_data);

      setTimeout(function() {
        var serialPort = new SerialPort('/dev/pts/2'/* match[1] */, {
          baudrate: 115200,
          databits: 8,
          stopbits: 1,
          parity: 'none',
          buffersize: 255
        });
        serialPort.on("open", function () {
          console.log('serial port open');
          var serial_data = '';
          var testsStartRegex = /CSPEC: starting tests/g;
          var testsEndRegex = /CSPEC: (\d*) tests failed/g;
          var starting = true;
          serialPort.on('data', function(data) {
            serial_data += data;
            if (starting) {
              var matchStart = serial_data.match(testsStartRegex);
              if (matchStart) {
                serial_data = serial_data.substring(serial_data.indexOf(matchStart[0]));
                process.stdout.write(serial_data);
                starting = false;
              }
            } else {
              process.stdout.write(data.toString());
              var matchEnd = testsEndRegex.exec(serial_data);
              if (matchEnd) {
                simduino.kill();
                process.exit(parseInt(matchEnd[1]));
              }
            }
          });
        });

        exec('avrdude -p m328p -c arduino -P /tmp/simavr-uart0 -U flash:w:build/test.hex', {},
        function(error, stdout, stderr) {
          console.log('avrdude stdout: ' + stdout);
          console.log('avrdude stderr: ' + stderr);
          if (error !== null) {
            console.log('avrdude exec error: ' + error);
          }
        });      
      }, 500);
    }
  });

  simduino.stdout.on('data', function (data) {
    console.log('simduino stdout: ' + data);
  });

  simduino.on('close', function (code) {
    console.log('simduino process exited with code ' + code);
  });
});
