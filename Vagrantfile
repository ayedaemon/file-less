# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|

  config.vm.box = "generic/ubuntu2004"
  config.vm.synced_folder ".", "/home/vagrant/workspace"

  config.vm.provider "virtualbox" do |vb|
    vb.name = "fileless"
    vb.gui = false
    vb.memory = "512"
    vb.linked_clone = true
  end

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get install -y \
      linux-headers-$(uname -r) \
      make
  SHELL
end
