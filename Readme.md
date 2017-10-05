# 42sh

_**By** apetitje, clabouri, hanguelk, oyagci_

## Features list

### Line edition :
1. Arrows (`LEFT` - `RIGHT`)
2. `Ctrl+L` / `Ctrl+D` / `Ctrl+C`
3. `Home` / `End`
4. Cut n Paste
	- `Ctrl+U`
	- `Ctrl+K`
	- `Ctrl+Y`
5. Move word by word
	- `alt+LEFT|RIGHT`
6. Move line by line
	- `alt+UP|DOWN`
7. `delete` / `suppr`

### Dynamic completion

### Bang Expansion
1. Event Designators:
	- `!`:
		* Start a history substitution, except when followed by a space, tab, the end of the line, `=` or `(`. 
	- `!n`:
		* Refer to command line n. 
	- `!-n`:
		* Refer to the command n lines back.
	- `!!`:
		* Refer to the previous command. This is a synonym for `!-1`.
	- `!string`:
		* Refer to the most recent command starting with string. 
	- `!?string[?]`:
		* Refer to the most recent command containing string. The trailing `?` can be omitted if the string is followed immediately by a newline. 
	- `^string1^string2^`:
		* Quick Substitution. Repeat the last command, replacing string1 with string2. Equivalent to `!!:s/string1/string2/`.
	- `!#`:
		* The entire command line typed so far.
2. Word Designators:
	- `0` (zero):
		* The 0th word. For many applications, this is the command word.
	- `n`:
		* The nth word. 
	- `^`:
		* The first argument; that is, word 1. 
	- `$`:
		* The last argument. 
	- `%`:
		* The word matched by the most recent `?string?` search. 
	- `x-y`:
		* A range of words; `-y` abbreviates `0-y`. 
	- `*`
		* All of the words, except the 0th. This is a synonym for `1-$`. It is not an error to use `*` if there is just one word in the event; the empty string is returned in that case. 
	- `x*`:
		* Abbreviates `x-$`. 
	- `x-`:
		* Abbreviates `x-$` like `x*`.
3. Modifiers:
	- `h`:
		* Remove a trailing pathname component, leaving only the head. 
	- `t`:
		* Remove all leading pathname components, leaving the tail. 
	- `r`:
		* Remove a trailing suffix of the form `.suffix`, leaving the basename.
	- `e`:
		* Remove all but the trailing suffix. 
	- `p`:
		* Print the new command but do not execute it. 
	- `q`:
		* Quote the substituted words, escaping further substitutions.
	- `x`:
		* Quote the substituted words as with `q`, but break into words at spaces, tabs, and newlines.
	- `s/old/new/`:
    		* Substitute new for the first occurrence of old in the event line. Any delimiter can be used in place of `/'. The delimiter can be quoted in old and new with a single backslash. If `&` appears in new, it is replaced by old. A single backslash will quote the `&`. The final delimiter is optional if it is the last character on the input line. 
	- `&`:
		* Repeat the previous substitution. 
	- `g`:
		* Cause changes to be applied over the entire event line. Used in conjunction with `s`, as in `gs/old/new/`, or with `&`.

### Reverse History search

### Builtins
1. `cd [-L|-P] [path]`
2. `echo [-n] [string ...]`
3. `setenv var value`
4. `unsetenv var`
5. `env [-i] [name=value] [utility[argument ...]]`
6. `exit [code]`
7. `read -s -r -e [-p arg] [-d arg] [-t arg] [-u arg] [-n arg]`
8. `history [-c] [-d offset] [-arnw filename]`
9. `hash [-lr] [-p pathname] [-dt] [name ...]`
10. `jobs [-lp][job_id ...]`
11. `bg [job_id]`
12. `fg [job_id]`
13. `dispvars`
14. `unset [-v][name ...]`
15. `export [-pn] [name[=value] ...]`

### Job Control
1. Suspend a jobs: `Ctrl + Z`
2. Resume a jobs:
	- in foreground: `fg [job id]`
	- in background: `bg [job id]`
3. View active jobs: `jobs [-lp][job_id ...]`

### Subshells

### Pipes

### Redirections & Heredoc

### Locales & inline vars

### Expansions
1. Vars
2. Command substitution
3. Globbing
	- Wildcards:
		* Star (`*` matching all using customized `matchnmatch`)
		* Question mark (`?` matching one character using customized `matchnmatch`)
	- Brackets expansion:
		* Basic (`[random_chars_to_match]`)
		* Ranges (like `[a-z]` or `[0-9]`)
		* Logical No (`[!...]`)
	- Braces expansion:
		* Basic (`{Exp1,Exp2,Exp3,...}`) (Expressions can be empty like `{,Expr2}`)
		* Letter and number ranges (`{a..z}` or `{0..100}` and more) (padding not supported)
4. Tilde
