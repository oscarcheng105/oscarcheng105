const mongoose = require('mongoose')
const { stringify } = require('querystring')

const RecipeSchema = new mongoose.Schema({
  recipeName: {
    type: String,
    required: true,
  },
  description: {
    type: String,
  },
  ingredients:{
    type: String,
    required: true,
  },
  tag:{
    type: Array,
    required: true,
  },
  procedures: {
    type: String,
    required: true,
  },
  userName:{
    type: String,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
})

module.exports = mongoose.model('Recipe', RecipeSchema)