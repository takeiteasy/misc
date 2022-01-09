#!/usr/bin/env ruby
# Search 
begin
  require 'nokogiri'
  require 'slop'
rescue
  abort "#{$0} requires slop and nokogiri - Please run 'gem install nokogiri slop'"
end

$opts = Slop.parse do |o|
  o.banner = " Usage: #{$0} [flags] [selector] [-f a:b:c] [-a href:title:src]"
  o.bool  '-h', '--help', 'Prints help'
  o.array '-f', '--files', 'Pass list of HTML/XML files', as: Array, delimiter: ':'
  o.bool  '-x', '--xpath', 'Specify XPath selector'
  o.array '-a', '--attr', 'Specify an attribute to print', as: Array, delimiter: ':'
  o.bool  '-t', '--text', 'Output contents of elements'
  o.bool  '-l', '--length', 'Output number of elements'
end

if $opts.help? 
  puts "\n#{$opts}\n"
  exit 0
end

unless $opts.arguments.length == 1
  puts "\n#{$opts}\n"
  puts "ERROR: No CSS selector or XPath supplied\n"
  exit 1
end
$selector = $opts.arguments[0].split(',').map(&:strip)

$type = $opts.xpath? ? :xpath : :css

def doit x
  length = 0
  $selector.each do |s|
    y = Nokogiri::HTML.parse(x).send($type, s)
    length += y.length
    if $opts.length?
     next 
    end
    y.each do |z|
      if $opts.attr?
        $opts[:attr].each do |a|
          b = z.attribute(a)
          unless b.to_s.to_s.strip.empty?
            puts b
          end
        end
      elsif $opts.text?
        unless z.content.empty?
          puts z.content
        end
      else
        o = z.to_s.split("\n").map(&:strip)
        unless o.empty?
          puts o.join()
        end
      end
    end
  end
  return length
end

length = 0
if $opts.files?
  $opts[:files].each do |x|
    length = doit File.read(x)
  end
else
  length = doit STDIN.readlines.join()
end

if $opts.length?
  puts length
end

