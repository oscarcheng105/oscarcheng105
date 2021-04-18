const path = require('path')
const express = require('express')
const mongoose = require('mongoose')
const dotenv = require('dotenv')
const morgan = require('morgan')
const session = require('express-session')
const MongoStore = require('connect-mongo')(session)
const cors = require('cors')
const bodyParser = require('body-parser')
const querystring = require('querystring')

const connectDB = require('./config/db')
const User = require('./models/User')
const Recipe = require('./models/Recipe')
const Comment = require('./models/Comment')

// Load config
dotenv.config({ path: './config/config.env' })

connectDB()

// EXPRESS
const app = express()

// BODYPARSER
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));

// CORS
app.use(cors());

// Logging
if (process.env.NODE_ENV === 'development') {
  app.use(morgan('dev'))
}

// Sessions
app.use(
  session({
    secret: 'keyboard cat',
    resave: false,
    saveUninitialized: false,
    store: new MongoStore({ mongooseConnection: mongoose.connection })
  })
)

// Routing

// Authentication/User
const { OAuth2Client } = require('google-auth-library')
const e = require('express')
const client = new OAuth2Client(process.env.GOOGLE_CLIENT_ID)

// @desc    Check DB if the user exist, if not, add user into the DB
// @route   POST /auth/google
app.post("/auth/google", async (req, res) => {
  const { token }  = req.body
    const ticket = await client.verifyIdToken({
        idToken: token,
        audience: process.env.GOOGLE_CLIENT_ID
    });
    const newUser = {
      googleId: ticket.getPayload().sub,
      displayName: ticket.getPayload().name,
      email: ticket.getPayload().email,
      image: ticket.getPayload().picture
    }
    try {
      let user = await User.findOne({ googleId: ticket.getPayload().sub })

      if (user) {
        console.log("There is already this user in the db")
      } else {
          user = await User.create(newUser)
          console.log("Creating a new user in the db")
      }
    } catch (err) {
      console.error(err)
    }
    res.sendStatus(200)
})

// @desc    Query User database and return the user info
// @route   GET /user
app.get("/user", (req, res) => {
  const url = querystring.parse(req.url);
  const googleId = url['/user?googleId'];
  
  User.find({ googleId: `${googleId}` }).then((user) => {
    res.send(user);
  }).catch((err) => {
    res.status(500).send(err);
  })
})

// Recipe
app.post("/dashboard", async (req, res) => {
  try{
    Recipe.create(req.body)
      .then(data => {
        res.json(data);
        console.log("Recipe Successfully Posted");
      })
  }catch(err){
    console.error(err);
  }
})

app.get("/recipe", (req, res) => {
  const url = querystring.parse(req.url);
  const id = url['/recipe?id'];

  if (typeof url['/recipe?id'] !== 'undefined') {
    try{
      Recipe.find({_id: `${id}`}).sort({ _id: -1 }).then((results => {
        res.send(results);
        //console.log(results);
      }))
    }catch(err){
      console.error(err)
    }
  } else {
    try{
      Recipe.find({}).sort({ _id: -1 }).then((results => {
        res.send(results);
        //console.log(results);
      }))
    }catch(err){
      console.error(err)
    }
  }
})

app.post("/comment", (req, res) => {
  try{
    Comment.create(req.body)
      .then(data => {
        res.json(data);
        console.log("Comment Successfully Posted");
      })
  }catch(err){
    console.error(err)
  }
})

app.get("/comment", (req, res) => {
  const url = querystring.parse(req.url);
  const id = url['/comment?id'];

  try{
    Comment.find({recipeID: `${id}`}).sort({ _id: -1 }).then((results => {
      res.send(results);
    }))
  }catch(err){
    console.error(err)
  }
})

// PORTS
const PORT = process.env.PORT || 9000

app.listen(
  PORT,
  console.log(`Server running in ${process.env.NODE_ENV} mode on port ${PORT}`)
)