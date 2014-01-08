include_recipe "build-essential"

package "libelf-dev"
package "gcc-avr"
package "avr-libc"
package "freeglut3"
package "freeglut3-dev"
package "git"

remote_file "#{Chef::Config[:file_cache_path]}/simavr-#{node[:simavr][:version]}.tar.gz" do
  source node[:simavr][:url]
end

bash "compile and install simavr" do
  cwd "/vagrant"
  user "vagrant"
  code <<-EOH
    tar -zxf #{Chef::Config[:file_cache_path]}/simavr-#{node[:simavr][:version]}.tar.gz
    cd simavr-#{node[:simavr][:version]}
    make all
    sudo make install
    EOH
  creates "/usr/local/bin/simavr"
end

