include_recipe "build-essential"

package "libelf-dev"
package "gcc-avr"
package "avr-libc"
package "freeglut3"
package "freeglut3-dev"
package "avrdude"
package "picocom"
package "xterm"
package "git"

magic_shell_environment 'SIMAVR_UART_XTERM' do
  value '1'
end

remote_file "#{Chef::Config[:file_cache_path]}/simavr-#{node[:simavr][:version]}.tar.gz" do
  source node[:simavr][:url]
end

directory node[:simavr][:install_dir] do
  owner node[:simavr][:user]
  group node[:simavr][:user]
  mode 0755
  recursive true
end

bash "compile and install simavr" do
  user node[:simavr][:user]
  code <<-EOH
    tar -zxf #{Chef::Config[:file_cache_path]}/simavr-#{node[:simavr][:version]}.tar.gz --strip-components=1 -C #{node[:simavr][:install_dir]}
    cd #{node[:simavr][:install_dir]}
    make all
    sudo make install
    EOH
  creates "/usr/local/bin/simavr"
end

magic_shell_environment 'SIMAVR_HOME' do
  value node[:simavr][:install_dir]
end
