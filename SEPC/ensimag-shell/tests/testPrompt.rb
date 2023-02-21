#!/usr/bin/ruby
# -*- coding: utf-8 -*-

# Copyright (C) 2013 Gregory Mounie
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

require "minitest/autorun"
require "expect"
require "pty"

require "../tests/testConstantes"

class Test0Prompt < Minitest::Test
  test_order=:defined

  def setup
    @pty_read, @pty_write, @pty_pid = PTY.spawn(COMMANDESHELL)
  end

  def teardown
    # ne rien faire
  end

  def test_ensiprompt
    # a = @pty_read.expect(PROMPT, DELAI)
    # refute_equal(nil, a, "Le prompt attendu est 'ensishell>' !")
  end

  def test_varianteNumber
    a = @pty_read.expect(/^Variante (\d+): (.*)\r/, DELAI)
    refute_nil(a, "Pas d'affichage donnant la variante")
    # puts "\nLa variante qui doit être implantée: #{a[1]} , #{a[2]}"
    test_ensiprompt()
    # a = @pty_read.expect(/.+/, DELAI)
    # assert_equal(nil, a, "Les printf intempestifs perturbent les tests")
  end

end
