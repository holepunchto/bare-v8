const binding = require('./binding')

exports.getHeapStatistics = function getHeapStatistics() {
  return binding.heapStatistics()
}
