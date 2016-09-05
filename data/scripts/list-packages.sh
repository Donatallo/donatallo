#!/bin/sh

case $(uname -s) in
FreeBSD)
	exec pkg query "%n"
	;;
Linux)
	if which dpkg-query >/dev/null 2>&1; then
		# Ubuntu, Debian
		exec dpkg-query --show --showformat='${Package}\n' '*'
	fi
	if which equery >/dev/null 2>&1; then
		# Gentoo, Calculate
		exec equery --quiet list --format='$name' '*'
	fi
	;;
esac

echo "Donatallo failed to get list of packages installed on your system" 1>&2
echo "This means that your system or distro is not supported yet" 1>&2
echo "Please file an issue in the project issue tracker:" 1>&2
echo 1>&2
echo "    https://github.com/Donatallo/donatallo-app/issues"
echo 1>&2
echo "and describe a way to retrieve list of installed packages for your system" 1>&2

exit 1
