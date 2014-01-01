#!/usr/bin/perl -w

#open file
open (FILE, "$ARGV[0]") or die "Could not open file";
@lines = <FILE>;

foreach $line (@lines) {
	chomp($line);
	
	#split string into two parts
	@string = split(', ', $line);
	
	#split expression on right into an array
	@exp = split('', $string[1]);
	
	#find and delete every occurrence of expression
	foreach $element (@exp){
		if($string[0] =~ m/$element/){
			$string[0] =~ s/$element//g;
		}
	}
	
	print "$string[0]\n";
}

close FILE;
