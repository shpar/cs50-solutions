from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    positive, negative, neutral = 0.0, 0.0, 100.0
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzer = Analyzer(positives, negatives)

    positive = analyzer.analyze(tweets)[1]
    negative = analyzer.analyze(tweets)[2]
    neutral = analyzer.analyze(tweets)[3]
    result = positive + negative + neutral
    positive = (positive / result) * 100.0
    negative = (negative / result) * 100.0
    neutral = (neutral / result) * 100.0
    
    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart = chart, screen_name = screen_name)
