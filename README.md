Utilities for computing curling sequences.

This directory contains various codes for computing features of curling
sequences.  More information about curling sequences can be found at:
  "On Curling Numbers of Integer Sequences", Chaffin, Linderman, Sloane, Wilks
  March 2013
  http://arxiv.org/abs/1212.6102

The work in this directory was the result of collaborations with Tong "Tony"
Liu '16 and Diwas Timilsina '16 during January and Spring of 2015.  Some
long-running computations were managed by Derrick Bonafilia.  Support was
received from the Divisional Research Funding Committee of Williams College.

UTILITIES
The following files form the core of the software:
  utils.{c,h} 	    - code for computing curling sequence information.
  		      there is support here for representations as general
		      arrays, strings, and 2-3 bits (more on this, below)
  ccurlseq	    - compute curling sequences from lines of general digits
   curlseq	    - array form
  cgen		    - generate all 2-3 bit strings of length n
   gen		    - array form of above
  choose n vals...  - print strings of n values chosen from vals with repeat
  drop [-]n	    - drop first [last] n values from each input array
  lens.py	    - computations of ideal long sequence lengths
  props		    - filter for 2-3 arrays: keep lines that meet P2,P3,P4
  quick		    - a dynamic programming approach; possibly quicker
  rotten	    - filter for rotten sequences; eg. gen 10 | rotten
  rotworker	    - see below; parallel rotten sequence discoverer
  span		    - utility for analyzing print span of repeats
  		      eg. ccurlseq | span
  spandist	    - generate span distance data per position (obsolete?)
  take		    - opposite of drop
