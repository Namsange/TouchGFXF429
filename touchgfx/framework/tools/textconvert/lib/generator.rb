###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
require 'lib/text_entries_excel_reader'
require 'lib/typographies_excel_reader'
require 'lib/sanitizer'
require 'lib/outputter'

class Generator
  def run(file_name, output_path, text_output_path, font_asset_path, data_format)
    text_entries = TextEntriesExcelReader.new(file_name).run
    typographies = TypographiesExcelReader.new(file_name).run
    Sanitizer.new(text_entries, typographies).run
    Outputter.new(text_entries, typographies, text_output_path, output_path, font_asset_path, data_format).run
  end
end
