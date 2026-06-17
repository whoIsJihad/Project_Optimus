#!/usr/bin/env bash
set -e

echo "=============================="
echo " FULL DOCKER CLEAN REINSTALL "
echo "=============================="

echo "1. Stopping services..."
sudo systemctl stop docker 2>/dev/null || true
sudo systemctl stop containerd 2>/dev/null || true

echo "2. Removing old Docker packages..."
sudo apt remove -y docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin || true
sudo apt autoremove -y

echo "3. Removing all Docker data (IMPORTANT CLEAN SLATE)..."
sudo rm -rf /var/lib/docker
sudo rm -rf /var/lib/containerd
sudo rm -rf /etc/docker

echo "4. Installing prerequisites..."
sudo apt update
sudo apt install -y ca-certificates curl gnupg

echo "5. Adding Docker official GPG key..."
sudo install -m 0755 -d /etc/apt/keyrings

curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg

echo "6. Adding Docker repository..."
echo \
"deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
$(. /etc/os-release && echo $VERSION_CODENAME) stable" | \
sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

echo "7. Installing Docker Engine..."
sudo apt update

sudo apt install -y \
  docker-ce \
  docker-ce-cli \
  containerd.io \
  docker-buildx-plugin \
  docker-compose-plugin

echo "8. Enabling services..."
sudo systemctl enable containerd
sudo systemctl enable docker
sudo systemctl start containerd
sudo systemctl start docker

echo "9. Fixing permissions (avoid sudo docker)..."
sudo usermod -aG docker $USER || true

echo "10. Verifying installation..."
docker --version
docker compose version

echo "11. Running test container..."
docker run hello-world

echo "=============================="
echo " INSTALLATION COMPLETE "
echo " PLEASE RELOGIN OR REBOOT "
echo "=============================="
