user node[:trezor_crypto][:user]

remote_file "#{Chef::Config[:file_cache_path]}/trezor-crypto.tar.gz" do
  source node[:trezor_crypto][:url]
end

directory node[:trezor_crypto][:install_dir] do
  owner node[:trezor_crypto][:user]
  group node[:trezor_crypto][:user]
  mode 0755
  recursive true
end

bash "unpack trezor-crypto source" do
  user node[:trezor_crypto][:user]
  code <<-EOH
    tar -zxf #{Chef::Config[:file_cache_path]}/trezor-crypto.tar.gz --strip-components=1 -C #{node[:trezor_crypto][:install_dir]}
    EOH
  creates ::File.join(node[:trezor_crypto][:install_dir], "Makefile")
end

magic_shell_environment 'TREZOR_CRYPTO_HOME' do
  value node[:trezor_crypto][:install_dir]
end
