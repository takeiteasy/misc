#!/usr/bin/env ruby
require "tty-prompt"

class Array
    def map_compact &block
        self.map { |e| yield e }.compact
    end
end

paths = ["~/Library/Application Support",
         "~/Library/Caches",
         "~/Library/Logs",
         "~/Library/Preferences",
         "~/Library/Containers",
         "~/Library/Cookies"]

$*.each do |app|
    unless app =~ /\.app\/?$/i
        puts "Ignoring argument \"#{app}\" must end with .app"
        next
    end
    unless File.exist? app
        puts "Ignoring argument \"#{app}\" doesn't exist"
        next
    end
    
    app_name = File.basename app
    files = paths.map_compact do |p|
        path = File.expand_path "#{p}/#{app_name.gsub /\.app\/?$/i, ""}"
        next nil unless Dir.exist? path
        path
    end
    puts files
end
