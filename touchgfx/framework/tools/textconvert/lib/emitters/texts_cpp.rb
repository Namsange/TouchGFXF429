###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
class TextsCpp < Template
  def countries
    text_entries.languages.map { |language| language.capitalize }
  end
  def countries_texts
    if countries.empty?
        "0"
    else
        countries.map{ |country| "texts#{country}" }.join(",\n    ")
    end
  end
  def is_rtl
    text_entries.is_rtl
  end
  def input_path
    File.join(root_dir,'Templates','Texts.cpp.temp')
  end
  def output_path
    'src/Texts.cpp'
  end
end
