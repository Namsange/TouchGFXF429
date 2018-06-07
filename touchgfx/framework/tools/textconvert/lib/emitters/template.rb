###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
require 'erb'
require 'lib/file_io'

class Template
  attr_accessor :text_entries
  attr_accessor :typographies

  def initialize(text_entries, typographies, output_directory)
    @text_entries = text_entries
    @typographies = typographies
    @output_directory = output_directory
  end
  def run
    result = ERB.new(File.read(input_path).
        gsub(WINDOWS_LINE_ENDINGS, UNIX_LINE_ENDINGS),0,"<>").result( binding ).
        gsub(WINDOWS_LINE_ENDINGS, UNIX_LINE_ENDINGS).
        gsub(UNIX_LINE_ENDINGS, LINE_ENDINGS)
    FileIO.write_file(File.join(@output_directory, output_path), result)
  end
end

