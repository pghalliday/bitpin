Vagrant.configure("2") do |config|

  # install chef solo on all machines
  config.omnibus.chef_version = :latest

  # enable berkshelf
  config.berkshelf.enabled = true

  config.vm.hostname = "bitpin"
  config.vm.box = "precise-server-cloudimg-amd64"
  config.vm.box_url = "http://cloud-images.ubuntu.com/vagrant/precise/current/precise-server-cloudimg-amd64-vagrant-disk1.box"
  config.ssh.forward_x11 = true

  # only use 1 core to prevent deadlocks in simavr
  config.vm.provider :virtualbox do |vb|
    vb.customize [
      "modifyvm", :id,
      "--memory", "1024",
      "--cpus", "1",
    ]
  end

  config.vm.provision :chef_solo do |chef|
    chef.json = {
      "nodejs" => {
        "install_method" => "package"
      }
    }
    chef.run_list = [
      "apt",
      "recipe[simavr]",
      "build-essential",
      "nodejs"
    ]
  end
end
