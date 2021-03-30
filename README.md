# tabular-parser
[![Build Status](https://semaphoreci.com/api/v1/ahmad88me/tabular-parser/branches/master/badge.svg)](https://semaphoreci.com/ahmad88me/tabular-parser)
[![codecov](https://codecov.io/gh/ahmad88me/tabular-parser/branch/master/graph/badge.svg)](https://codecov.io/gh/ahmad88me/tabular-parser)

parse CSV, TSV, ... etc into transposed list of list

# Methods
* `parse_vertical()`: parse the CSV file and access it row by row. Each row is returned as a list of strings.
* `parse()`: parse the CSV file and access it column by column. 

# Build
`make`

# Install
`make install`

# Run tests
`make test`

# Example
If you already installed it, you can run the example `example.cpp`. Else, you can run the `make.cpp`. You can also pass the csv parameter to the executable `parser.out` as a parameter.

# Sample run
```
Parsing: test-q.csv
Horizonal mode: 

"height" 180 172 192 
----------
"weight" 60 70 90 
----------
"name" AAA BBB CCC 
----------

Vertical mode: 

"height" "weight" "name" 
----------
180 60 AAA 
----------
172 70 BBB 
----------
192 90 CCC 
----------

```



