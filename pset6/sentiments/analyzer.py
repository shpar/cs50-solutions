import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # print(positives)
        tokenizer = nltk.tokenize.TweetTokenizer()
        pos = []
        neg = []
        with open(positives) as lines:
            for line in lines:
                if line[0].isalpha():
                    string = line.strip()
                    pos.append(string)

        with open(negatives) as lines:
            for line in lines:
                if line[0].isalpha():
                    string = line.strip()
                    neg.append(string)        
        self.pos = pos
        self.neg = neg

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        score, positive, negative, neutral = 0, 0, 0, 0
        for tweet in text:
            tokens = tokenizer.tokenize(tweet)
            
            for token in tokens:
                token = token.lower()
                if token.isalpha():
                    if token in self.pos:
                        score += 1
                        positive += 1
                    elif token in self.neg:
                        score -= 1
                        negative += 1
                    else:
                        neutral += 1
        return [score, positive, negative, neutral]
        
    def analyzeWord(self, word):
        """Analyze word for sentiment, returning its score."""
        for entry in self.pos:
            if word == entry:
                return 1
        for entry in self.neg:
            if word == entry:
                return -1
        return 0
