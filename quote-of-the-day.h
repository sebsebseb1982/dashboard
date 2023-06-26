#ifndef QUOTE_OF_THE_DAY_H
#define QUOTE_OF_THE_DAY_H

struct QuoteOfTheDay {
  String quote;
  String author;
};

class QuoteOfTheDayService {
public:
  static QuoteOfTheDay get();
private:
};

#endif