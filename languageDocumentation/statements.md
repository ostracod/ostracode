
# Statements

This page documents behavior statements and attribute statements in OstraCode.

## Behavior Statements

OstraCode has the following behavior statements:

### Variable Statements:

```
prep $name <$type> [$attrs] = <$initItem>
```

Declares a prep-grade variable with name identifier `$name`, constraint type `$type`, and initialization item `$initItem`. If `<$type>` is excluded, then the constraint type of the variable will be the type of `$initItem`.

```
var $name <$type> [$attrs] = ($initItem)
```

Declares a flow-grade variable with name identifier `$name`, constraint type `$type`, and initialization item `$initItem`. If `<$type>` is excluded, then the constraint type of the variable will be the type of `$initItem`. If `= ($initItem)` is excluded, then the initial item of the variable will be `null`. If both `<$type>` and `= ($initItem)` are excluded, then the constraint type of the variable will be `itemT`.

### Expression Statement:

```
($expr)
```

Evaluates expression `$expr` to achieve a side-effect.

### Scope Statement:

```
{$behavior}
```

Evaluates `$behavior` in a nested scope.

### If Statement:

```
if ($condition1) {$behavior1} elseIf ($condition2) {$behavior2} else {$behavior3}
```

If `$condition1` is true, then `$behavior1` is evaluated. Otherwise if `$condition2` is true, `$behavior2` is evaluated. If neither `$condition1` nor `$condition2` are true, then `$behavior3` is evaluated. `elseIf ($condition2) {$behavior2}` may be excluded or repeated any number of times. `else {$behavior3}` may be excluded.

### Loop Statements:

```
while ($condition) {$behavior}
```

Enters a loop evaluating `$behavior` until `$condition` is false.

```
for $name in ($iterable) {$behavior}
```

Iterates over each member in `$iterable`, assigning the member to a flow-grade variable with name identifier `$name` and evaluating `$behavior`. The type of `$iterable` must conform to `(*IterableT)`.

### Loop Control Statements:

```
break
```

Stops the current iteration of the parent loop statement, and exits the loop.

```
continue
```

Stops the current iteration of the parent loop statement, and jumps to the beginning of the loop again.

### Return Statement:

```
return ($item)
```

Stops evaluation of the parent function, and returns item `$item`. If `($item)` is excluded, then the return item is `null`.

### Error Statements:

```
try {$behavior1} catch $name {$behavior2} finally {$behavior3}
```

Attempts to evaluate `$behavior1`. If `$behavior1` throws an error, the error will be stored in a flow-grade variable with name identifier `$name`, and `$behavior2` will be evaluated. The constraint type of the variable is `(*ErrorT)`. Regardless of whether any error occurred, `$behavior3` will be evaluated. Either `catch $name {$behavior2}` or `finally {$behavior3}` may be excluded, but not both.

```
throw ($error)
```

Throws error `$error` which will be handled by a `try` statement. The type of `$error` must conform to `(*ErrorT)`.

### Entry Point Statement:

```
entryPoint <$func>
```

Declares that the entry point of the current package is `$func`. The entry point function will be invoked when running the current package as an application.

### Import Statements:

```
importPath <$path> as $moduleName [$attrs]
```

Imports the module located at file path `$path` in the current package. `$path` is relative to the `src` directory of the current package. The module will be exposed as a prep-grade variable with name identifier `$moduleName` in the current module. If `as $moduleName` is excluded, the module will not be exposed as a variable.

```
importBuiltIn <$name> as $moduleName [$attrs]
```

Imports the built-in module with name string `$name`. The module will be exposed as a prep-grade variable with name identifier `$moduleName` in the current module. If `as $moduleName` is excluded, the module will not be exposed as a variable.

```
importPackage <$specifier> as $moduleName [$attrs]
```

Imports the main module of the package in `~/.ostraCodePackages` with specifier string `$specifier`. The module will be exposed as a prep-grade variable with name identifier `$moduleName` in the current module. If `as $moduleName` is excluded, the module will not be exposed as a variable.

## Attribute Statements

OstraCode has the following attribute statements:

### List Value Statements:

Valid contexts for list value statements:

* `list` special

```
elemType <$type>
```

Asserts that the type of each element in the parent list value conforms to `$type`.

```
length <$length>
```

Asserts that the number of elements in the parent list value is `$length`.

### List Type Statements:

Valid contexts for list type statements:

* `listT` special

```
elemType ($type)
```

Asserts that the type of each element in the parent list type conforms to `$type`.

```
length ($length)
```

Asserts that the number of elements in the parent list type is `$length`.

### Arguments Statement:

```
args [$args]
```

Valid contexts:

* `func` and `funcT` specials
* `method` and `methodT` specials
* `generic` and `genericT` specials

Declares the arguments which the parent function or generic may accept.

### Argument Statements:

```
$name <$type> [$attrs] = ($defaultItem)
```

Valid contexts:

* `args` statement in one of the following contexts:
    * `func` special
    * `method` special
    * `genericT` special

Declares an argument with name identifier `$name`, constraint type `$type`, and default item `$defaultItem`. If `<$type>` is excluded, then the constraint type of the argument will be the type of `$defaultItem`. If `= ($defaultItem)` is excluded, then the default item will be `null`. If both `<$type>` and `= ($defaultItem)` are excluded, then the constraint type of the argument will be `itemT`.

```
$name <$type> [$attrs] = <$defaultItem>
```

Valid contexts:

* `args` statement in `generic` special

Declares an argument with name identifier `$name`, constraint type `$type`, and default item `$defaultItem`. If `<$type>` is excluded, then the constraint type of the argument will be the type of `$defaultItem`. If `= <$defaultItem>` is excluded, then the default item will be `null`. If both `<$type>` and `= <$defaultItem>` are excluded, then the constraint type of the argument will be `itemT`.

```
$name ($type) [$attrs]
```

Valid contexts:

* `args` statement in one of the following contexts:
    * `funcT` special
    * `methodT` special

Declares an argument with name identifier `$name` and constraint type `$type`. If `($type)` is excluded, then the constraint type of the argument will be `itemT`.

### Returns Statements:

```
returns <$type>
```

Valid contexts:

* `func` special
* `method` special

Asserts that the parent function value returns an item whose type conforms to `$type`. The default return type is `nullT`.

```
returns ($type)
```

Valid contexts:

* `funcT` special
* `methodT` special

Asserts that the parent function type returns an item whose type conforms to `$type`. The default return type is `nullT`.

### Field Type Statements:

```
fieldType <$type>
```

Valid contexts:

* `dict` special

Asserts that the type of each field in the parent dictionary value conforms to `$type`.

```
fieldType ($type)
```

Valid contexts:

* `dictT` special

Asserts that the type of each field in the parent dictionary type conforms to `$type`.

### Fields Statements:

```
fields [$fields]
```

Valid contexts:

* `dict` and `dictT` specials
* `interfaceT` special
* `feature` and `featureT` specials

Declares fields which are stored in each instance of the parent dictionary or factor.

```
sharedFields [$fields]
```

Valid contexts:

* `interfaceT` special
* `feature` and `featureT` specials

Declares fields which are shared between all instances of the parent factor.

### Field Statements:

```
$name <$type> [$attrs] = ($initItem)
```

Valid contexts:

* `fields` statement in `dict` or `feature` specials
* `sharedFields` statement in `feature` special

Declares a field with name identifier `$name`, constraint type `$type`, and initialization item `$initItem`. If `<$type>` is excluded, then the constraint type of the field will be the type of `$initItem`. If `= ($initItem)` is excluded, then the initial item of the field will be `null`. If both `<$type>` and `= ($initItem)` are excluded, then the constraint type of the field will be `itemT`.

```
($key) <$type> [$attrs] = ($initItem)
```

Valid contexts:

* `fields` statement in `dict` special

Declares a dictionary field whose key is the item returned by `$key`, and otherwise uses the same rules as described above.

```
$name ($type) [$attrs]
```

Valid contexts:

* `fields` statement in `dictT` special:
* `fields` and `sharedFields` statements in one of the following contexts:
    * `interfaceT` special
    * `featureT` special

Declares a field with name identifier `$name` and constraint type `$type`. If `($type)` is excluded, then the constraint type of the field will be `itemT`.

```
($key) ($type) [$attrs]
```

Valid contexts:

* `fields` statement in `dictT` special

Declares a dictionary field whose key is the item returned by `$key`, and otherwise uses the same rules as described above.

### Optional Statement:

```
optional
```

Valid contexts:

* Argument statement
* Field statement in `dict` or `dictT` special

Asserts that the parent argument or field is optional.

### Self Feature Statements:

```
selfFeature <$featureType>
```

Valid contexts:

* `method` special

Asserts that the type of `self` is `objT ($featureType)` when referenced in the body of the method. `$featureType` must conform to `featureT`.

```
selfFeature ($featureType)
```

Valid contexts:

* `methodT` special

Asserts that the type of `self` is `objT ($featureType)` when referenced in the body of the method. `$featureType` must conform to `featureT`.

### This Factor Statements:

```
thisFactor <$factorType>
```

Valid contexts:

* `feature` special
* `method` special

Asserts that the type of `this` is `objT ($factorType)` when referenced in the body of a method. `$factorType` must conform to `factorT`.

```
thisFactor ($factorType)
```

Valid contexts:

* `featureT` special
* `methodT` special

Asserts that the type of `this` is `objT ($factorType)` when referenced in the body of a method. `$factorType` must conform to `factorT`.

### Factors Statement:

```
factors [$factors]
```

Valid contexts:

* `bundle` and `bundleT` specials

Asserts that the parent bundle contains the factors specified by `$factors`.

### Factor Statement:

```
($factor) [$attrs]
```

Valid contexts:

* `factors` statement

Asserts that the parent bundle contains factor `$factor`.

### Permission Statements:

Valid contexts for permission statements:

* Field statement in one of the following contexts:
    * `interfaceT` special
    * `feature` or `featureT` special

```
public
```

Asserts that the parent field is accessible in all contexts.

```
protected
```

Asserts that the parent field is accessible only by features in the same bundle.

```
private
```

Asserts that the parent field is accessible only by methods in the same feature.

### Visibility Statements:

```
vis <$vis>
```

Valid contexts:

* Field statement in `feature` special

Asserts that the visibility of the parent field is `$vis`. The default visibility is 1.

```
vis ($vis)
```

Valid contexts:

* Field statement in one of the following contexts:
    * `interfaceT` special
    * `featureT` special

Asserts that the visibility of the parent field is `$vis`. The default visibility is 1.

### Shield Statements:

```
shield <$amount>
```

Valid contexts:

* Factor statement in `bundle` special

Asserts that the visibility of fields in the parent factor value should be decreased by `$amount`. The default shield amount is 1.

```
shield ($amount)
```

Valid contexts:

* Factor statement in `bundleT` special

Asserts that the visibility of fields in the parent factor type should be decreased by `$amount`. The default shield amount is 1.

### Implements Statements:

```
implements <$interfaceType>
```

Valid contexts:

* `feature` special

Asserts that the parent feature value declares the fields and methods of interface type `$interfaceType`.

```
implements ($interfaceType)
```

Valid contexts:

* `featureT` special

Asserts that the parent feature type declares the fields and methods of interface type `$interfaceType`.

```
implements <$factorTypes>
```

Valid contexts:

* `bundle` special

Asserts that the parent bundle value includes features which satisfy factor types `$factorTypes`.

```
implements ($factorTypes)
```

Valid contexts:

* `bundleT` special

Asserts that the parent bundle type includes features which satisfy factor types `$factorTypes`.

### Exported Statement:

```
exported
```

Valid contexts:

* Variable statement at top level of module
* `importPath`, `importBuiltIn`, and `importPackage` statements
* Member statement

Asserts that the parent member may be imported by other modules from the current module.

### Members Statement:

```
members [$members]
```

Valid contexts:

* `importPath`, `importBuiltIn`, and `importPackage` statements

Declares the members to import from the external module.

### Member Statement:

```
$name1 as $name2 [$attrs]
```

Valid contexts:

* `members` statement

Declares that the member with name identifier `$name1` in the external module will be exposed with name identifier `$name2` in the current module. If `as $name2` is excluded, then the member will use name identifier `$name1` in the current module. 


