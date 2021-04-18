const mongoose = require('mongoose')

const CommentSchema = new mongoose.Schema({
  userName: {
    type: String,
    required: true,
  },
  message:{
    type: String,
    required: true,
  },
  recipeID:{
    type: Object,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
})

module.exports = mongoose.model('Comment', CommentSchema)