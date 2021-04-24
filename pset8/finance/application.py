import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    idportfolio = db.execute("SELECT * FROM portfolio WHERE id= :id", id = session['user_id'])
    #for i in range(0,len(idportfolio)):
        #pstock = idportfolio[i]['symbol']
        #pshares = idportfolio[i]['shares']
        #pvalue = idportfolio[i]['price']
    return render_template("index.html", idportfolio = idportfolio)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        ticker = request.form.get("symbol")

        #Check whether valid ticker is entered.
        if lookup(ticker)['symbol'] == None:
            return apology("Please enter a valid ticker.")

        # Check if sufficient cash to make transaction
        currentcash = db.execute("SELECT cash FROM users WHERE id= :id", id = session['user_id'])
        #Confirm if sufficient cash to make transaction
        if currentcash[0]['cash'] - int(request.form.get('shares'))*int(lookup(ticker)['price']) < 0:
            return apology("You do not have enough cash to perform this transaction.")
        else:
            # Check whether existing row in table 'portfolio'
            checkshares = db.execute("SELECT * FROM portfolio WHERE id = :id AND symbol = :symbol", id = session['user_id'], symbol = request.form.get("symbol"))
            formsymbol = request.form.get("symbol")
            formshares = request.form.get("shares")

            # Insert data into table 'portfolio' if not yet exsists and update cash in 'users'
            if len(checkshares) == 0:
                db.execute("INSERT INTO portfolio (id, symbol, shares, price) VALUES(:id, :symbol, :shares, :price)", id = session['user_id'], symbol = formsymbol, shares = formshares, price = float(formshares)*lookup(formsymbol)['price'])
                newcash = currentcash[0]['cash'] - float(formshares)*int(lookup(ticker)['price'])
                db.execute(f"UPDATE users SET cash = {newcash} WHERE id =:id", id = session['user_id'])
                return apology("Success!")
                db.execute("INSERT INTO transactions (id, symbol, shares, value, transacted) VALUES(:id, :symbol, :shares, :value, :transacted)", id = session['user_id'], symbol = formsymbol, shares = formshares, value = (float(formshares)*lookup(formsymbol)['price']), transacted = datetime.now())
                # Update table 'portfolio' if already exists and update cash in 'users'
            else:
                newshares = int(checkshares[0]['shares']) + int(request.form.get('shares'))
                newprice = newshares * lookup(request.form.get('symbol'))['price']
                db.execute(f"UPDATE portfolio SET shares = {newshares}, price = {newprice} WHERE id =:id AND symbol =:symbol", id = session['user_id'], symbol = request.form.get("symbol"))
                newcash = currentcash[0]['cash'] - float(formshares)*int(lookup(ticker)['price'])
                db.execute(f"UPDATE users SET cash = {newcash} WHERE id =:id", id = session['user_id'])
                db.execute("INSERT INTO transactions (id, symbol, shares, value, transacted) VALUES(:id, :symbol, :shares, :value, :transacted)", id = session['user_id'], symbol = formsymbol, shares = formshares, value = (float(formshares)*lookup(formsymbol)['price']), transacted = datetime.now())

                return apology("success!")

    else:
        return render_template("buy.html")



@app.route("/history", methods=["GET", "POST"])
@login_required
def history():
    """Show history of transactions"""

    usertransactions = db.execute("SELECT * FROM transactions WHERE id =:id", id = session['user_id'])
    #for i in range(0, len(usertransactions)):
        #pstock = usertransactions[i]['symbol']
        #pshares = usertransactions[i]['shares']
        #pvalue = usertransactions[i]['value']
        #pdate = usertransactions[i]['transacted']

    return render_template("history.html", transact = usertransactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        ticker = request.form.get("symbol")
        namet = lookup(ticker)['name']
        symbolt = lookup(ticker)['symbol']
        pricet = lookup(ticker)['price']
        return render_template("quoted.html", namet=namet, symbolt=symbolt, pricet=pricet)
    else:
        return render_template("quote.html")


@app.route("/quoted")
@login_required
def quoted():
    return render_template("quoted.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        #Check if all fields in form have been filled
        myvar = ['name', 'email', 'username', 'password']
        for var in myvar:
            if not request.form.get(f"{var}"):
                return apology(f"Please provide a {var}", 403)
             #Check if username and password are confirmed correctly
            elif request.form.get("username") != request.form.get("confirm-username"):
                return apology("Please confirm username")
            elif request.form.get("password") != request.form.get("confirm-password"):
                return apology("Please confirm username")

        rowcheck = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rowcheck) != 0:
            return apology("This username is taken, please enter a different username.", 403)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))
            return apology("success!")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    ticker = db.execute("SELECT * FROM portfolio WHERE id =:id", id = session['user_id'])

    if request.method == "POST":
        #Check if sufficient shares to sell
        reqsellsymbol = request.form.get('symbol')
        reqsellqty = request.form.get('shares')
        availqty = db.execute("SELECT * FROM portfolio WHERE id =:id AND symbol =:symbol", id = session['user_id'], symbol = reqsellsymbol)
        if availqty[0]['shares'] < int(reqsellqty):
            return apology("You do not have sufficient shares to perform this transaction")
        else:

            #Update table 'portfolio' with updated stocks and price
            newshares = availqty[0]['shares'] - int(reqsellqty)
            sellprice = float(newshares) * lookup(reqsellsymbol)['price']
            db.execute(f"UPDATE portfolio SET shares = {newshares}, price = price - {sellprice}) WHERE id =:id AND symbol =:symbol", id = session['user_id'], symbol = reqsellsymbol)
            #Update table users with new cash
            newcash = sellprice
            db.execute(f"UPDATE users SET cash = cash + {newcash} WHERE id =:id", id = session['user_id'])
            #Update transactions to show latest transaction
            db.execute("INSERT INTO transactions (id, symbol, shares, value, transacted) VALUES(:id, :symbol, :shares, :value, :transacted)", id = session['user_id'], symbol = reqsellsymbol, shares = -int(reqsellqty), value = (float(reqsellqty)*lookup(reqsellsymbol)['price']), transacted = datetime.now())
            return apology("Success!")
    else:
        return render_template("sell.html", ticker=ticker)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
