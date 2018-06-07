###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
require 'lib/file_io'
require 'lib/emitters/template'
require 'lib/emitters/text_keys_and_languages_hpp'
require 'lib/emitters/texts_cpp'
require 'lib/emitters/languages_cpp'
require 'lib/emitters/unicodes_txt'
require 'lib/emitters/fonts_cpp'
require 'lib/emitters/application_font_provider_hpp'
require 'lib/emitters/application_font_provider_cpp'
require 'lib/emitters/typed_text_database_hpp'
require 'lib/emitters/typed_text_database_cpp'

class Outputter
  def initialize(text_entries, typographies, localization_output_directory, fonts_output_directory, font_asset_path, data_format)
    @text_entries = text_entries
    @typographies = typographies
    @localization_output_directory = localization_output_directory
    @fonts_output_directory = fonts_output_directory
    @font_asset_path = font_asset_path
    @data_format = data_format
  end

  def run

    [ UnicodesTxt,
      ApplicationFontProviderCpp,
      ApplicationFontProviderHpp ].each { |template| template.new(@text_entries, @typographies, @fonts_output_directory).run }

    [ TextKeysAndLanguages,
      TextsCpp,
      LanguagesCpp,
      TypedTextDatabaseHpp,
      TypedTextDatabaseCpp ].each { |template| template.new(@text_entries, @typographies, @localization_output_directory).run }

    FontsCpp.new(@text_entries, @typographies, @fonts_output_directory, @font_asset_path, @data_format).run

  end
end

