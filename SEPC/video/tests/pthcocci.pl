#!/usr/bin/perl -w

use v5.16;
use strict;
use warnings;

my $commande= "spatch --sp-file ../tests/pthcheck.cocci --very-quiet ../src/synchro.c";

my $nb=0;

open(my $fd, "-|", "$commande | egrep '^-[^-]' | wc -l")
  or die "Houla ? : $!";
$nb = <$fd>;
close $fd;

if ($#ARGV == -1 || $ARGV[0] ne "--quiet") {
	system("$commande");
}
exit -1 if ($nb > 0);
exit 0;

