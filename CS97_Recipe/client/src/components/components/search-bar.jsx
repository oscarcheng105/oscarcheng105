import React, { Component, useEffect, useState } from "react";
import Recipe from "./recipes.jsx";
import style from "../css/App.css";


// ID to fetch recipes from example database
const APP_ID = '12ffae8f';
const APP_KEY = 'd9a0ee10a194b1c7edd5764fdfab3c46';

class App extends React.Component {

  state = {
    recipes: [],
    search: "",
    query: ""
  };

  // API Database fetching
  async fetchingQuery() {
    const responseFromAPI = await fetch(
      `https://api.edamam.com/search?q=${this.state.query}&app_id=${APP_ID}&app_key=${APP_KEY}`);

    const data = await responseFromAPI.json();
    console.log(data.hits);
    this.setState({ recipes: data.hits });
  };

  updateSearch = newSearch => {
    this.setState({ search: newSearch.target.value });
    //console.log(this.state.search);
  };

  submitSearch = event => {

    event.preventDefault();
    this.state.query = this.state.search;
    // alert("input: " + this.state.query);
    this.setState({ search: "" });

    this.fetchingQuery();
  }

  render() {
    return (
      <div className="App">
        <form onSubmit={this.submitSearch} className="search-form">
          <input className="search-bar" type="text" value={this.state.newSearch} onChange={this.updateSearch} />
          <button className="search-button" type="submit">
            Search
        </button>
        </form>
        <div className="recipes">
          {this.state.recipes.map(recipe => (
            <Recipe
              key={recipe.recipe.label}
              title={recipe.recipe.label}
              calories={recipe.recipe.calories.toFixed(2)}
              image={recipe.recipe.image}
              ingredients={recipe.recipe.ingredients} />
          ))}
        </div>
      </div>
    );
  }
}

export default App;