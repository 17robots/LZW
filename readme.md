# Cryptography Hashing

## Description
The project is designed to demonstrate the RSA Encryption's application of document signing. The project offers the ability to generate the values for the RSA encryption, sign a document, and verify the document compared to the original signature.

## Installation
With the source files installed in the destination directory, run the following command to make both parts of the project:

`make all`

If you want to make a specific version of the project, run 1 of the following commands:

`make lzw`

`make lzwm`

In order to clean up the build files, run the following command:

`make clean`

## Capabilities And Usage
### Part1
#### Compression
`./lzw c [filename]`
In order to compress a file, the 'c' flag must be used along with the name of the file (including extension) to compress. You can compress any file type with the command. Then, when the compression is done, it will be written out to [filename].lzw

#### Decompression
`./lzw e [filename]`
In order to decompress a file, the 'e' flag must be used along with the name of the file (including extension). The file that gets decompressed *must* be a .lzw file. When decompressed the content will be written out to [filename]2

#### Help
`./lzw h`
This will print out the help menu for the program. It includes the different options available and provides an example for usage.

#### Example
Compress case1.txt:

`./lzw c case1.txt`
This produces the following files:

- case0.txt.lzw
- log.txt
- log2.txt

Decompress case0.txt.lzw

`./lzw e case1.txt.lzw`

This produces the following files:

- case0.txt.lzw2
- log.txt (rewritten)
- log2.txt (rewritten)

Getting Help:
`./lzw h`

This produces the following output:
```
Help for lzw command:

Usage: lzw [option] [filename]
Available Options:
e or E: - expand a lzw file and print out the expanded message

c or C: - compress a file and export out to a file called [filename].lzw

h or H: - print this help message

```

### Part2
#### Compression
`./lzwm c [filename]`
In order to compress a file, the 'c' flag must be used along with the name of the file (including extension) to compress. You can compress any file type with the command. Then, when the compression is done, it will be written out to [filename].lzw2

#### Decompression
`./lzwm e [filename]`
In order to decompress a file, the 'e' flag must be used along with the name of the file (including extension). The file that gets decompressed *must* be a .lzw file. When decompressed the content will be written out to [filename]2M

#### Example
Compress case1.txt:

`./lzw c case1.txt`
This produces the following files:

- case0.txt.lzw2
- log.txt
- log2.txt

Decompress case0.txt.lzw2

`./lzw e case1.txt.lzw`

This produces the following files:

- case0.txt.lzw22M
- log.txt (rewritten)
- log2.txt (rewritten)

Getting Help:
`./lzw h`

This produces the following output:
```
Help for lzwm command:

Usage: lzwm [option] [filename]
Available Options:
e or E: - expand a lzw file and print out the expanded message

c or C: - compress a file and export out to a file called [filename].lzw2

h or H: - print this help message

```

### Possible Errors And Checks
There are a couple of errors that can be thrown due to misuse:

#### Error. There is no signature file present.
This happens when the signature file cannot be found. This can be fixed by resigning the file.

#### Error. Possible file deletion after signing.
This happens when the RSA files are deleted after a document has been signed. This can be fixed by either regenerating the RSA values and resigning the file or just resigning the file.

#### Check to backup failed. This will result in incorrect verification.
This happens when either the file backup is not found after a document was signed or the values for the RSA are different than what was used to sign the document before. This can be fixed by signing the file again.

#### Invalid argument. Number expected.
This happens when the last argument when generating the RSA values with the g flag is not a number. Re generate providing a number argument.

#### wrong format! should be "a.exe s filename"
This happens when the second argument is not g, s, or v. Rerun with either of those to get more specific errors.

### Additional Notes
I am including a test.html file that is larger than the other files to show the speed of the program. I am also including cat.jpg for the bonus points associated with non character based signing and verifying.