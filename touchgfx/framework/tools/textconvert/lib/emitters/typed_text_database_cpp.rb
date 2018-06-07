###############################################################################
# This file is part of the TouchGFX 4.9.3 distribution.
# Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
###############################################################################
# This is licensed software. Any use hereof is restricted by and subject to 
# the applicable license terms. For further information see "About/Legal
# Notice" in TouchGFX Designer or in your TouchGFX installation directory.
###############################################################################
class TypedTextDatabaseCpp < Template
  TypedTextPresenter = Struct.new(:alignment, :direction, :typography)

  def typed_texts(language)
    text_entries.collect do |entry|
        typography_name = entry.typographies[language] || entry.typography
        typography = typographies.find { |t| t.name == typography_name }
        alignment = entry.alignments[language] || entry.alignment
        direction = entry.directions[language] || entry.direction
        TypedTextPresenter.new(alignment, direction, typography);
    end
  end

  def layouts
    if text_entries.empty?
      ["DEFAULT"]
    else
      (text_entries.first.typographies.keys + text_entries.first.alignments.keys + text_entries.first.directions.keys << "DEFAULT").uniq
    end
  end

  def fonts
   typographies.map{ |t| Typography.new("", t.font_file, t.font_size, t.bpp) }.uniq.collect do |f|
      "getFont_#{f.cpp_name}_#{f.font_size}_#{f.bpp}bpp"
    end
  end

  def fontmap
    fontmap = Hash.new
    fonts.each_with_index do |f, i|
      fontmap[f] = i
    end
    fontmap
  end

  def input_path
    File.join(root_dir,'Templates','TypedTextDatabase.cpp.temp')
  end
  def output_path
    'src/TypedTextDatabase.cpp'
  end
end
