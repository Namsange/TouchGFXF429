###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
require 'lib/excel_reader'
require 'lib/typographies'

class TypographiesExcelReader
  attr_reader :reader

  def initialize(file_name)
    header_row_number = 3
    header_column_number = 2
    @reader = ExcelReader.new(file_name, "Typography", header_row_number, header_column_number)
    @typographies = []
  end

  def run
    reader.read_rows do |row|
      name = row[:"Typography Name"]
      font = row[:font]
      size = row[:size]
      bpp = row[:bpp]
      if row.exists?(:"Fallback Character")
        fallback_character = row[:"Fallback Character"]
      end
      if row.exists?(:"Wildcard Characters")
        wildcard_characters = row[:"Wildcard Characters"]
      end
      if row.exists?(:"Character Ranges") # New name
        wildcard_ranges = row[:"Character Ranges"]
      elsif row.exists?(:'Wildcard Ranges') # Old name
        wildcard_ranges = row[:'Wildcard Ranges']
      end
      if row.exists?(:'Ellipsis Character')
        ellipsis_character = row[:'Ellipsis Character']
      end

      if name
        name = name.strip
        unless name.match(/^([0-9a-zA-Z_])*$/)
          fail "Illegal characters found in Text ID '#{name}'"
        end
      end
      font = font.strip if font
      size = size.strip if size
      bpp = bpp.strip if bpp
      fallback_character = fallback_character.strip if fallback_character
      wildcard_characters = wildcard_characters.strip if wildcard_characters
      wildcard_ranges = wildcard_ranges.strip if wildcard_ranges
      ellipsis_character = ellipsis_character.strip if ellipsis_character

      if name && font && size && bpp
        @typographies.push Typography.new(name, font, size.to_i, bpp.to_i, fallback_character, ellipsis_character, wildcard_characters, wildcard_ranges)
      end
    end
    @typographies
  end

end
