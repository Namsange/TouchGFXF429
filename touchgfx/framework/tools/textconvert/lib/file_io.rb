###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
require 'rubygems'
require 'erb'
require 'fileutils'
require 'pathname'


class FileIO
  def self.write_file(file_name, contents)
    FileUtils.mkdir_p(File.dirname(file_name))
    File.open(file_name, 'w') { |f| f.write(contents) }
    callingPath = Pathname.new($calling_path)
    filePath = Pathname.new(file_name)
    puts "Generating #{filePath.relative_path_from(callingPath)}"
  end
end
