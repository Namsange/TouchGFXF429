###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
class FontsCpp
  def self.font_convert=(font_convert)
    @@font_convert = font_convert
  end

  def initialize(text_entries, typographies, output_directory, font_asset_path, data_format)
    @typographies = typographies
    @output_directory = output_directory
    @font_asset_path = font_asset_path
    @data_format = data_format
  end
  def run
    unique_typographies = @typographies.map{ |t| Typography.new("", t.font_file, t.font_size, t.bpp, t.fallback_character, t.ellipsis_character) }.uniq

    unique_typographies.sort_by { |t| sprintf("%s %04d %d",t.font_file,t.font_size,t.bpp) }.each do |typography|
      fonts_directory = File.expand_path(@output_directory)
      font_file = File.expand_path("#{@font_asset_path}/#{typography.font_file}")
      fallback_char = typography[:fallback_character]
      fallback_char ||= 0
      ellipsis_char = typography[:ellipsis_character]
      ellipsis_char ||= 0
      cmd = "\"#{@@font_convert}\" \
-f \"#{font_file}\" \
-w #{typography.font_size} \
-r #{typography.font_size} \
-o \"#{fonts_directory}\" \
-c \"#{@output_directory}/UnicodeList#{typography.cpp_name}_#{typography.font_size}_#{typography.bpp}.txt\" \
-n \"#{typography.cpp_name}\" \
-b #{typography.bpp} \
-d #{fallback_char} \
-e #{ellipsis_char} \
-#{@data_format}"

      output = `#{cmd}`
      if !$?.success?
        puts cmd
        puts output
        raise "Error generating font from #{font_file}"
      elsif output.match(/WARNING/i)
        puts output
      end
    end
  end
end
