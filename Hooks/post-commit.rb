#!/usr/bin/env ruby

# This post commit hook triggers a build on the build server

require 'socket'
ip = '192.168.0.10'
port = 1490
conn = TCPSocket.open(ip, port)
conn.write('Request Build')
conn.close_write