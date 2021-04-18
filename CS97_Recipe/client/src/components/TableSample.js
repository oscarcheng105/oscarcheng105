import React from 'react'
import { withRouter } from "react-router-dom";
import Grid from '@material-ui/core/Grid';
import {Paper, makeStyles, Card, CardHeader, CardContent, Typography, Button, CardActions, InputAdornment, Toolbar } from '@material-ui/core'
import useTable from '../components/components/useTable'
import Controls from './components/controls/Controls';
import { Search } from '@material-ui/icons';
import * as tagsArray from "./tag/tagsArray.js"

const useStyles = makeStyles(theme =>({

    table: {
        marginTop: theme.spacing(3),
        '& tbody td':{
            fontWEight: '300'
        },
    },
    pageContent:{
        margin: theme.spacing(5),
        padding: theme.spacing(3),
        '& .MuiFormControl-root':{ //& is a selector symobl, . is for all classes
            width: '15%'
            ,margin: theme.spacing(1)
        }
    },
    searchInput:{
        width: '75%',
        margin: theme.spacing(1)
    },
    searchContainer:{
        display: 'flex',
        
    },
    select: {
        '& .MuiFormControl-root':{ //& is a selector symobl, . is for all classes
            width: '200px',
            margin: theme.spacing(1)
        }
    }
}))

export function TableSample(props){

    const classes = useStyles()
    const [ingredients, setIngredients] = React.useState(props.recipeList)
    const [filter, setFilter] = React.useState("")
    const handleSearchChange = e => {
        console.log(e.target.textContent)
        setFilter(e.target.textContent)
        console.log(filter)
    }
    const handleChange = (e) => {
        console.log(e.target.value)
        setFilter((e.target.value).toLowerCase())
    }
    const{
        TblContainer, TblPagination, recordsAfterPagingAndSorting
    }= useTable()
    return(
        <Paper className = {classes.pageContent}>
            <Toolbar>
                <Controls.Select
                    name = "Tags"
                    label = "Tags"
                    value = {props.tag}
                    options= {tagsArray.getTagsArray()}
                    className = {classes.select}
                    InputProps = {{
                        startAdornment: (<InputAdornment position="start">
                            <Search />
                        </InputAdornment>)
                    }}
                    onChange = {handleChange}
                />
            </Toolbar>
            <Grid
                    container
                    spacing={2}
                    direction="row"
                    justify="flex-start"
                    alignItems="flex-start"
            >
                {props.recipeList.map((recipe, i) => (
                        JSON.stringify(recipe.tag).toLowerCase().includes(filter) && 
                        (JSON.stringify(recipe.recipeName).toLowerCase().includes(props.search) ||
                        JSON.stringify(recipe.userName).toLowerCase().includes(props.search)) &&
                        <Grid item xs={12} sm={6} key={i}>
                            <Card>
                                <CardHeader
                                    title={recipe.recipeName}
                                    subheader={(recipe.createdAt).substring(0, 10)}
                                />
                                <CardContent>
                                    <Typography variant="body2" color="textSecondary" component="p">
                                        {recipe.description}
                                    </Typography>
                                    <br/>
                                    <Typography variant="body2" color="textSecondary" component="p">
                                        {" Tag: " + recipe.tag}
                                    </Typography>
                                </CardContent>
                                <CardActions>
                                    <Button onClick={() => {console.log(recipe._id); props.history.push(`/Recipe?id=${recipe._id}`)}} size="small">
                                        Learn More
                                    </Button>
                                </CardActions>
                            </Card>
                        </Grid>
                    ))}
            </Grid>
        </Paper>
    )

}


export default withRouter((TableSample))