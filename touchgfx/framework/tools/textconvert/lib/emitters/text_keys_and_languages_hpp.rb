###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
class TextKeysAndLanguages < Template
  def countries
    text_entries.languages.map { |language| language.upcase }.join(",\n    ")
  end
  def texts
    text_entries.entries.map(&:cpp_text_id)
  end
  def input_path
    File.join(root_dir,'Templates','TextKeysAndLanguages.hpp.temp')
  end
  def output_path
    'include/texts/TextKeysAndLanguages.hpp'
  end
end
