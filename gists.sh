#!/usr/bin/env sh
# Relies on jq + curl

function pages {
  echo "($1 + $2 - 1) / $2" | bc
}

for user in $@; do
	path="$(pwd)/$(echo "$user")"
	if test ! -d "$path"; then
		mkdir "$path"
	fi
	npages=$(pages $(curl -s "https://api.github.com/users/$user" | jq -r '.public_gists') 30)
	for (( i=1; i<=$npages; i++ )); do
		curl -s "https://api.github.com/users/$user/gists?page=$i" | jq -c ".[]" | while IFS='' read file; do
			path="$(pwd)/$(echo "$user")"
			nfiles=$(echo "$file" | jq -r ".files | length")
			if test $nfiles -gt 1; then
				path="$(echo "$path")/$(echo "$file" | jq -r "[.files[]] | .[0].filename" | cut -d '.' -f 1)"
				if test ! -d "$path"; then
					mkdir "$path"
				fi
			fi
			echo "$file" | jq -r ".files[].raw_url" | while read -r url; do
				curl "$url" -o "$(echo "$path")/$(echo "$url" | rev | cut -d '/' -f 1 | rev)"
			done
		done
	done
done
