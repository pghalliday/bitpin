package "arduino"
package "arduino-core"

user node[:arduino][:user] do
  gid "dialout"
  action :modify
end
