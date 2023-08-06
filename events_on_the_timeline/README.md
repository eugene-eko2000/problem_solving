# Number of Events on the Timeline

## Description
There is a long timeline e.g. billions of years, an age of the Earth. And there are events that happen during this timeline, e.g. earthquakes. Events don't come in a chrono order, sometimes past earthquakes become known.

Each earthquake has one property, magnitude. Let's have magnitudes as integers, from 1 to 12.

The problem is to build a structure that will answer the query: **return the number of earthquakes of each magnitude during the given time period**. The time period granularity is in years. The time period is defined as ```year_start```, ```year_end```, inclusive.

### Example
```
Events: [
  [1100, 7],
  [1425, 7],
  [1425, 5],
  [1718, 6],
  [1834, 7],
  [1868, 6],
  [1900, 6]
]

Input: [1300, 2000]

Output: {
  5: 1,
  6: 3,
  7: 2 
}
```