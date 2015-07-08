var
  md5 = require('MD5'),
  fs = require('fs');

function createIndex(str) {
  var i, index = {}, chr;
  for (i = 0; i < str.length; i++) {
    chr = str[i];
    index[chr] = (index[chr] || 0) + 1;
  }
  return index;
}

function indexContains(index, subIndex) {
  var chr;
  for (chr in subIndex) {
    if (subIndex.hasOwnProperty(chr) && (!index.hasOwnProperty(chr) || subIndex[chr] > index[chr])) {
      return false;
    }
  }
  return true;
}

function excludeIndex(index, subIndex) {
  var newIndex = {}, chr, value, empty = true;
  for (chr in index) {
    if (index.hasOwnProperty(chr)) {
      value = index[chr];
      if (subIndex.hasOwnProperty(chr)) {
        value -= subIndex[chr];
      }
      if (value) {
        newIndex[chr] = value;
        empty = false;
      }
    }
  }
  return empty ? null : newIndex;
}

function uniqueByProperty(items, property) {
  return items.filter(function (item, index) {
    var i, value = item[property];
    for (i = 0; i < index; i++) {
      if (items[i][property] === value) {
        return false;
      }
    }
    return true;
  });
}

function findAnagram(charsIndex, dict, prevWords, targetHash) {
  var i, item, nextCharsIndex, result, words;  
  dict = dict.filter(function (item) {
    return indexContains(charsIndex, item.index);
  });  
  if (!prevWords.length) {    
    dict = uniqueByProperty(dict, 'word');
  }  
  for (i = 0; i < dict.length; i++) {
    item = dict[i];
    nextCharsIndex = excludeIndex(charsIndex, item.index);
    words = prevWords.concat(item.word);
    if (nextCharsIndex) {
      result = findAnagram(nextCharsIndex, dict, words, targetHash);
      if (result) {
        return result;
      }
    } else {
      result = words.join(' ');
      if (md5(result) === targetHash) {
        return result;
      }
    }
  }
  return null;
}

var      
  dict = fs.readFileSync('./data/wordlist.txt', 'utf8').split('\n')
    .filter(function (str) {
      return str.replace(/ /, '');
    })
    .map(function (word) {
      return {word: word, index: createIndex(word)};
    }),
  initialStr = "poultry outwits ants",
  finalMD5 = "4624d200580677270a54ccff86b9610e",    
  result = findAnagram(createIndex(initialStr.replace(/ /, '')), dict, [], finalMD5); 

console.log(result);