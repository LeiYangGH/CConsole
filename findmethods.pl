#!/usr/bin/perl

use 5.010;
use strict;
use warnings;
use File::Path;
use File::Glob ':glob';
#use Array::Utils qw(:all);
use File::Basename;
use File::Spec::Functions 'catfile';
 use File::Find qw(finddepth);

my $testdir = 'C:/test';
 # my $cdir = 'C:/G/CConsole/CStu';
my $cdir = 'C:/G/CConsole';
my @files;

finddepth(sub 
{
      return if($_ eq '.' || $_ eq '..');
      push @files, $File::Find::name;
}, $cdir);
for my $f (@files)
{
        if(!-d $f &&  $f =~ /\.cpp$/)
        { 
        	 
		
		   open(FILE, $f);  
		    while (<FILE>) 
		    {
			 if (
			 $_ =~ /readall/
			# $_ =~ /get/ && 
			 #$_ =~ /\w+\s\w+\(.*?\)/
			 )
			 {
			  say "-------------$f";
			    say "$&";
			    # print "$fullname\n\n";
			 }
		    }
	}
	}
	
	      

print "Hello World!\n";
