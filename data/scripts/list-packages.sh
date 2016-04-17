#!/bin/sh

case $(uname -s) in
FreeBSD)
	exec pkg query "%n"
	;;
Linux)
	;;
esac
