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
        	 my $found = 0;
		
		   open(FILE, $f);  
		   
		    while (<FILE>) 
		    {
			 if (
			 $_ =~ /localtime/
			# $_ =~ /get/ && 
			 #$_ =~ /\w+\s\w+\(.*?\)/
			 )
			 {
			 
			  $found = 1;
			    say "$&";
			    # print "$fullname\n\n";
			 }
		    }
		    if($found)
		    {
		      say "-------------$f";
		     }
	}
	}
	
	      

print "Hello World!\n";
