function greaterThan(num) {
 return function(y) {
    return y > x;
  };
}

var greaterThanTen = greaterThan(10);
show(greaterThanTen(9));

