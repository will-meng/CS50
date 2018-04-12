# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

an artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust

## According to its man page, what does `getrusage` do?

get resource usage

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

so we don't need to use memory to create a copy, since this is a read only operation

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

the for loop is just a while loop in disguise with 4 main parts:
1) initial code (int c = fgetc(file)): initialize a variable of type int and assign the first character of file to that variable
2) while loop condition (c != EOF): run the loop body as long as this evaluates to true
3) loop body: 
  a) check if c is a letter or an apostrophe. if so, copy it into the word buffer in increment the index of buffer. 
  b) if the index is too high (i.e. word is too long) or a number is found, "seek" through the file so we can skip the rest of this word's characters
     and reset index so a new word can be stored in the word buffer
  c) if the character is neither a letter, number, or apostrophe, we believe we have found the end of a word (as long as this is not the first character of the file). 
     Add the null terminator to the word buffer, increment our word count, and run our benchmarks/spell-checker on this word.
     Reset the index to 0 so that a new word can overwrite the existing contents of the word buffer.
4) at the bottom of the loop body, run this code (c = fgetc(file)), which gets the next character, then go back to step 2

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

we would have to go back and check each character one by one anyways in order to find numbers or punctuation in the string

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

we don't want to potentially mutate the original characters of the string
