# Name Generator

A mad-libs style text generator based on configurable grammars.

Usage:

```bash
./text-generator <path to dat file>
```

# Grammar Syntax
The beauty of this program is its configurability. You can generate anything from names,
to faux English words to character backstories. The mechanism here is essentially
strings of tokens chosen at random from predefined lists. The tokens can be simple
strings or complex arrangements of strings and other tokens.

The syntax of the grammar files is based on an INI file, with embellishments
described below.

When a grammar file is parsed, a line is selected at random from the [MAIN]
section. In turn, each token (as indicated by being surrouded by angular braces < and >),
is expanded.

Token expansion is defined by other sections. A section consists of a header 
like [TokenType] and subsequent lines representing possible values of tokens of
that type. Lines may include other token types.

When a token is expanded from a list, a line is selected at random from that
section, any necessary token expansion is done on it, and then the resulting
string is used as the full value of that token.

## Referenced Tokens
In more complicated grammars, the user may want to refer back to the same value
of a previously-generated token. For example, in a backstory generation grammar,
the program keeps track of the generated name of the character in question. This
is done by adding a *reference tag* to the token in question. The first time
the reference tag is used in a token, its expansion gets stored. In subsequent
times the reference tag is used, the first, stored expansion gets used instead
of producing another token expansion.

A reference tag is appended to the name of the token type by a '$', like so: `<TokenType$referencetag>`.
Additional references will be the exact same, i.e. `<TokenType$referencetag>`.

## Example

For example, let's say we want to generate a character backstory. Our story consists
of a character name, a hometown, and a favorite activity. Our grammar might look
like this:

```
[MAIN]
<Name$name> grew up in <Place$hometown> and loved to <Activity>. One day, <Name$name> will go back to <Place$hometown> again.
[Name]
Sally
Jimmy
Bobby
Petunia

[Place]
Paris
Logan
New York

[Activity]
go bowling
have lunch with <Name>
watch movies
```
