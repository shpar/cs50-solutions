from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    u_id = session["user_id"]
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=u_id)
    total = 0
    for row in rows:
        info = lookup(row["symbol"])
        row["price"] = usd(info["price"])
        row["name"] = info["name"]
        row["total"] = usd(info["price"] * row["number"])
        total += info["price"] * row["number"]
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=u_id)    
    total += cash[0]["cash"]
    return render_template("index.html", rows=rows, cash=usd(cash[0]["cash"]), total=usd(total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":

        # ensure stock was submitted
        if not request.form.get("stock"):
            return apology("must provide stock")
        if not request.form.get("number"):
            return apology("must provide number of stocks")        
        if not request.form.get("number"):
            return apology("must provide stock")
        number = request.form.get("number")
        if not (number.isdigit() and int(number) > 0):
            return apology("stock number must be positive number")
        info = lookup(request.form.get("stock"))
        if not info:
            return apology("stock information cannot be found")
        number = int(number)
        u_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=u_id)
        price = info["price"]
        if cash[0]["cash"] < number * price:
            return apology("insufficient funds")
        
        
        rows = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id AND symbol = :symbol", user_id=u_id, 
            symbol = request.form.get("stock"))
        if len(rows) == 0:
            db.execute("INSERT INTO portfolio (user_id, symbol, number) VALUES(:user_id, :symbol, :number)", user_id=u_id, 
                symbol=request.form.get("stock"), number=number)
        else:
            db.execute("UPDATE portfolio SET number = number + :number WHERE user_id = :user_id AND symbol = :symbol", number=number, 
                user_id=u_id, symbol = request.form.get("stock"))
            
        db.execute("UPDATE users SET cash = cash - :number * :price WHERE id = :id", id=u_id, number=number, price=price)
        db.execute("INSERT INTO transactions (user_id, symbol, number, price) VALUES(:user_id, :symbol, :number, :price)", user_id=u_id, 
            symbol=request.form.get("stock"), number=number, price=price)
        
        return redirect(url_for("index"))
        
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    u_id = session["user_id"]
    rows = db.execute("SELECT * FROM transactions WHERE user_id=:user_id", user_id=u_id)
    for row in rows:
        info = lookup(row["symbol"])
        row["name"] = info["name"]
        row["price"] = usd(row["price"])

    return render_template("history.html", rows=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # ensure stock was submitted
        if not request.form.get("stockname"):
            return apology("must provide stock")
        
        info = lookup(request.form.get("stockname"))
        if not info:
            return apology("stock information cannot be found")
        
        return render_template("quoted.html", name=info["name"], price=usd(info["price"]), symbol=info["symbol"])
        
    else:
        return render_template("quote.html")
        
    return apology("TODO")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    """OD TU DALJE CP"""
    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
            
        elif not request.form.get("password2"):
            return apology("must repeat password")
            
        elif not request.form.get("password") == request.form.get("password2"):
            return apology("passwords do not match")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 0:
            return apology("username already taken")
        
        hash = pwd_context.hash(request.form.get("password2"))
        
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=hash)
        
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    
    # return apology("TODO")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":

        # ensure stock was submitted
        if not request.form.get("stock"):
            return apology("must provide stock")
        if not request.form.get("number"):
            return apology("must provide number of stocks")        
        if not request.form.get("number"):
            return apology("must provide stock")
        number = request.form.get("number")
        if not (number.isdigit() and int(number) > 0):
            return apology("stock number must be positive number")
        
        u_id = session["user_id"]
        number = int(number)
        rows = db.execute("SELECT number FROM portfolio WHERE user_id = :user_id AND symbol = :symbol", user_id=u_id, 
            symbol = request.form.get("stock"))
        if len(rows) == 0:
            return apology("stock is not in portfolio")
        elif rows[0]["number"] < number:
            return apology("cannot sell more stocks than there are in the portfolio")
                
        info = lookup(request.form.get("stock"))
        price = info["price"]
        
        db.execute("UPDATE portfolio SET number = number - :number WHERE user_id = :user_id AND symbol = :symbol", number=number, 
                user_id=u_id, symbol = request.form.get("stock"))
        db.execute("UPDATE users SET cash = cash + :number * :price WHERE id = :id", id=u_id, number=number, price=price)
        db.execute("INSERT INTO transactions (user_id, symbol, number, price) VALUES(:user_id, :symbol, :number, :price)", user_id=u_id, 
                symbol=request.form.get("stock"), number= -number, price=price)        
        if rows[0]["number"] == number:
            db.execute("DELETE FROM portfolio WHERE user_id = :user_id AND symbol = :symbol", user_id=u_id, symbol = 
                request.form.get("stock"))
        return redirect(url_for("index"))
        
    else:
        return render_template("sell.html")

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "POST":

        # ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password")
            
        if not request.form.get("password2"):
            return apology("must repeat password")
            
        elif not request.form.get("password") == request.form.get("password2"):
            return apology("passwords do not match")
        u_id = session["user_id"]
        hash = pwd_context.hash(request.form.get("password2"))
        
        db.execute("UPDATE users SET hash = :hash WHERE id = :id", hash=hash, id=u_id)

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("password.html")
