import React, { useEffect } from 'react';
import { makeStyles } from '@material-ui/core/styles';
import List from '@material-ui/core/List';
import ListItem from '@material-ui/core/ListItem';
import ListItemIcon from '@material-ui/core/ListItemIcon';
import ListItemSecondaryAction from '@material-ui/core/ListItemSecondaryAction';
import ListItemText from '@material-ui/core/ListItemText';
import ListSubheader from '@material-ui/core/ListSubheader';
import Checkbox from '@material-ui/core/Checkbox';
import IconButton from '@material-ui/core/IconButton';
import CommentIcon from '@material-ui/icons/Comment';
import Collapse from '@material-ui/core/Collapse';
import InboxIcon from '@material-ui/icons/MoveToInbox';
import DraftsIcon from '@material-ui/icons/Drafts';
import SendIcon from '@material-ui/icons/Send';
import ExpandLess from '@material-ui/icons/ExpandLess';
import ExpandMore from '@material-ui/icons/ExpandMore';
import StarBorder from '@material-ui/icons/StarBorder';
import Divider from '@material-ui/core/Divider';
import Typography from '@material-ui/core/Typography';
import Card from '@material-ui/core/Card';
import CardHeader from '@material-ui/core/CardHeader';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import Button from '@material-ui/core/Button';

const useStyles = makeStyles((theme) => ({
  root: {
    width: '100%',
    maxWidth: 240,
    backgroundColor: theme.palette.background.paper,
  },
}));


export default function CheckboxList(props) {
  const classes = useStyles();

  useEffect(()=> {
    console.log("value of props changed: ", props.checkArray)
  }, [props.checkArray])

  return (
    <List className={classes.root}>
      {[0, 1, 2, 3].map((value) => {
        const labelId = `checkbox-list-label-${value}`;

        return (
          <ListItem key={value} role={undefined} dense button onClick={props.handleCheckClick(value, props.checkArray)}>
            <ListItemIcon>
              <Checkbox
                edge="start"
                checked={props.checkArray[value]}
                tabIndex={-1}
                disableRipple
                inputProps={{ 'aria-labelledby': labelId }}
              />
            </ListItemIcon>
            <ListItemText id={labelId} primary={`Ingredient  ${value + 1}`} />
          </ListItem>
        );
      })}
    </List>
  );
}

export function NestedList(props) {
  const classes = useStyles();
  const [open, setOpen] = React.useState(false);
  const handleClick = () => {
    setOpen(!open);
  };

  return (
    <List>
      <ListItem button onClick={handleClick}>
        <ListItemIcon>
          <InboxIcon />
        </ListItemIcon>
        <ListItemText primary= {props.name} />
        {open ? <ExpandLess /> : <ExpandMore />}
      </ListItem>
      <Collapse in={open} timeout="auto" unmountOnExit>
        <List component="div" disablePadding>
          <ListItem button className={classes.nested}>
            <CheckboxList  checkArray = {props.checkArray} handleCheckClick = {props.handleCheckClick} />
          </ListItem>
        </List>
      </Collapse>
    </List>
  );
}

export class SelectedList extends React.Component{
  constructor(props){
    super(props);
    this.handleListItemClick = this.handleListItemClick.bind(this);
    this.state={
      ingredients: props.ingredientsArray,
      selectedIndex: 0,
      output: this.props.output
    }
  }

  handleListItemClick(index){
    this.setState({selectedIndex:index});
  }
  renderIngredients(){
    return this.state.ingredients.map(el => {
      return (<ListItem button 
        key={el.index}
        selected = {this.state.selectedIndex===el.index} 
        onClick = {index => this.handleListItemClick(el.index)}>
          <NestedList name = {el.name} checkArray = {el.chk}  
          handleCheckClick = {this.props.handleCheckClick}
          />
        </ListItem>)

    })
  }
  render(){
    const {classes}=this.props;
    return(
      <div>
      <List
        component="nav"
        aria-labelledby="nested-list-subheader"
        subheader={
          <ListSubheader component="div" id="nested-list-subheader">
            Ingredients
          </ListSubheader>
        }
      >
        {this.renderIngredients()}
        </List>
        </div>
    )
  }
}