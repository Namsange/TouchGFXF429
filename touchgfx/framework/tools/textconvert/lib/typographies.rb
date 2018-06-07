###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
class Typography < Struct.new(:name, :font_file, :font_size, :bpp, :fallback_character, :ellipsis_character, :wildcard_characters, :wildcard_ranges)
  def cpp_name
    font_file.gsub(/\.ttf$/,"").gsub(".", "_").gsub(" ", "_").gsub("-","_")
  end
end
