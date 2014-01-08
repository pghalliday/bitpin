include_recipe "build-essential"

package "libelf-dev"
package "avr-libc"
package "git"

remote_file "#{Chef::Config[:file_cache_path]}/simavr-#{node[:simavr][:version]}.tar.gz" do
  source node[:simavr][:url]
end

bash "compile and install simavr" do
  cwd "opt/"
  code <<-EOH
    tar -zxf #{Chef::Config[:file_cache_path]}/simavr-#{node[:simavr][:version]}.tar.gz
    cd simavr-#{node[:simavr][:version]}
    make
    make install
    EOH
  creates "/usr/local/bin/simavr"
end

