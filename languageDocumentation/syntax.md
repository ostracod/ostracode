
# Syntax

This page documents expression syntax and statement syntax in OstraCode.

## Expression Syntax

OstraCode supports the following types of expressions:

* Value literal
* Variable identifier
* Unary operation with one operand expression
* Binary operation with two operand expressions
* Binary operation with an expression and an identifier
* Binary operation with an expression and an expression sequence
* Function, method, and special invocations
* Expression sequence which returns one item

Value literals include the following:

* Decimal number consisting of digits and an optional decimal point (`.`)
* Hexadecimal number consisting of digits with the prefix `0x`
* String enclosed by quotation marks (`"`)
* Character enclosed by apostrophes (`'`)

Value literals have the following constraint types:

* The constraint type of integer literals and character literals is `intT`.
* The constraint type of floating-point number literals is `floatT`.
* The constraint type of string literals is `strT`.

To create types which refer to specific values, use the `literalT` function. See the section on built-in functions for more details.

Identifiers and keywords may contain the following characters:

* Uppercase and lowercase letters
* Underscore (`_`)
* Dollar sign (`$`)
* Decimal digits

Note that identifiers may not begin with a decimal digit. Also note that throughout this documentation, an identifier beginning with a dollar sign denotes a placeholder. A dollar sign does not otherwise hold special significance.

## Expression Sequences

An "expression sequence" consists of expressions enclosed by bracket delimiters. Expressions in an expression sequence are separated by commas or newlines. Every expression sequence returns an item sequence.

The bracket delimiters used in an expression sequence determine the following properties:

* The evaluation grade of expressions in the expression sequence
* The return items of the expression sequence

OstraCode includes the following expression sequence bracket delimeters:

* `(` and `)` enclose flow-grade expressions, and return the items returned by the expressions.
* `(*` and `)` enclose flow-grade expressions, and return item types whose factor types are the items returned by the expressions.
* `<` and `>` enclose prep-grade expressions, and return the items returned by the expressions.
* `<?` and `>` enclose never-grade expressions, and return the constraint types of the expressions. The return items are known during prep-phase of the parent context.
* `<*$expr>` is equivalent to `<(*$expr)>`.
* `<*?$expr>` is equivalent to `<*<?$expr>>`.

Expression sequences provide arguments to functions, methods, specials, qualifications, and statements. An expression sequence which returns one item can serve as an expression, and may be nested in other expressions.

With regard to statement arguments and expression operands, bracket delimiters follow these compatibility rules:

* `(*` and `)` may be used in any context which accepts `(` and `)`.
* `<` and `>` may be used in any context which accepts `(` and `)`.
* `<?` and `>` may be used in any context which accepts `<` and `>`.

For example, given that the structure of a return statement is defined to be `return ($item)`, the form `return <$item>` is also valid.

## Statement Syntax

OstraCode has two types of statements:

* "Behavior statements" declare variables, perform operations, and determine control flow.
* "Attribute statements" define properties of data structures.

A "statement sequence" consists of statements enclosed by bracket delimiters. Statements in a statement sequence are separated by commas or newlines. The bracket delimiters determine the type of statements which the statement sequence contains:

* `{` and `}` enclose behavior statements.
* `[` and `]` enclose attribute statements.

Each statement contains one or more of the following components:

* Keyword
* Identifier
* Expression sequence
* Statement sequence
* Equal sign

Note that attribute statement sequences are always optional in statements, and may be excluded when empty.

A comment with the prefix `--` may be placed at the end of any line.

## Invocation Syntax

A function invocation accepts an argument item sequence, and returns an item. A function may be invoked by placing an expression sequence after an expression which returns the function. For example, `$func($exprs)` invokes `$func` using the items returned by `$exprs`. Method invocation uses the same syntax as function invocation.

A "special" is an identifier which may be invoked in a similar fashion to a function. A special accepts both expression sequences and statement sequences which are placed immediately after the special. For example, `$special [$attrs] ($exprs)` invokes `$special` with both `[$attrs]` and `($exprs)`.

Note that attribute statement sequences are always optional in specials, and may be excluded when empty.

Unlike functions, specials are always invoked when embedded in an expression, even when they do not precede an expression sequence or statement sequence. For example, `($special)` invokes `$special`. As a result, specials cannot be passed as items. Instead, only the items returned by their invocation can be passed.


