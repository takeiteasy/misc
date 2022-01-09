#!/usr/bin/env ruby
require "tty-prompt"
require "slop"

class Array
    def map_compact &block
        self.map { |e| yield e }.compact
    end
end
    
opts = Slop.parse do |o|
    o.banner = "\nUsage: #{$0} --image <image> [options]\n"
    o.string '-i', '--image', 'Path to the desired image for writing (required)', required: true
    o.separator ""
    o.array '-d', '--disks', 'List of disks to write to (optional, deliminater: ",")', deliminater: ','
    o.string '-n', '--name', 'Name of the volume (optional, default: "BOOTUSB") (If program is writing to multiple disks will auto increment prefixed number)'
    o.separator ""
    o.bool '-x', '--delete-iso', 'If .iso is passed to -i, delete after it is converted', default: false
    o.bool '-c', '--delete-img', 'Delete the image file after write (original+converted images are deleted)', default: false
    o.bool '-a', '--delete-all', 'Enables -x and -c', default: false
    o.on '-h', '--help', "Print this message\n" do
        puts o
        exit
    end
end
opts[:x] = opts[:c] = true if opts[:a]

final_name = name = opts[:name].nil? ? "BOOTUSB" : opts[:name].upcase
raise "Invalid volume name supplied: \"#{final_name}\" Please use alpha-numeric names" unless final_name =~ /^[A-Z0-9]+$/
name_inc = 0

raise "ERROR: Image \"#{opts[:image]}\"" unless File.exists? opts[:image]
case File.extname opts[:image]
when ".iso"
    img = opts[:image].gsub /.iso$/i, ".img"
    puts `hdiutil convert -format UDRW "#{opts[:image]}" -o "#{img}"`
    dmg = "#{img}.dmg"
    `mv "#{dmg}" "#{img}"` if !File.exist? img and File.exist? dmg
    if opts[:x]
        puts "Flag -x enabled, deleting original .iso file: #{opts[:image]}"
        File.delete opts[:image]
    end
    opts[:image] = img
when ".img"
    puts "Using image: #{opts[:image]}"
else
    raise "ERROR: Invalid image, IMG+ISO files only"
end
exit 1

all_disks = `diskutil list`.scan(/\/dev\/disk(\d+)/).map { |n| n[0].gsub /(\/dev\/)?(\/?disk)/, "" }
opt_disks = opts[:disks].map_compact do |d|
    /^(\/dev\/)?(\/?disk)?(?<n>\d+)$/ =~ d
    if n.nil?
        puts "Ignoring argugment to --disk: \"#{d}\" invalid syntax"
        next nil
    elsif !all_disks.include? n
        puts "Ignoring argugment to --disk: \"#{d}\" doesn't exist"
        next nil
    end
    n
end

if opt_disks.empty?
	prompt = TTY::Prompt.new
    opt_disks = prompt.multi_select("Choose the disk you want to write to: /dev/disk", all_disks, filter: true, cycle: true)
end

final_name = "#{name}#{name_inc}" if opt_disks.length > 1
opt_disks.each do |disk|
    puts `diskutil unmountDisk /dev/disk#{disk}`
    puts `diskutil eraseDisk FAT32 #{final_name} /dev/disk#{disk}`
    puts `dd if="#{opts[:image]}" of=/dev/rdisk#{disk} bs=1m`
    puts `diskutil eject /dev/disk#{disk}`
    puts "/dev/disk#{disk} finished!"
    if opt_disks.length > 1
        name_inc += 1
        final_name = "#{name}#{name_inc}"
    end
end

if opts[:c]
    puts "Flag -c enabled, deleting created .img file: #{opts[:image]}"
    File.delete opts[:image]
end
