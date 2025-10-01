const test = require('brittle')
const v8 = require('.')

test('heap statistics', (t) => {
  t.comment(v8.getHeapStatistics())
})

test('heap space statistics', (t) => {
  t.comment(v8.getHeapSpaceStatistics())
})
