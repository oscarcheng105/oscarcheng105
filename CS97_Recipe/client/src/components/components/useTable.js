import { makeStyles, Table, TablePagination } from '@material-ui/core'
import {useState} from 'react'

const useStyles = makeStyles(theme =>({

    table: {
        marginTop: theme.spacing(3),
        '& tbody td':{
            fontWEight: '300'
        },
    },

    pageContent:{
        margin: theme.spacing(5),
        padding: theme.spacing(3)
    }
}))

export default function useTable (records, headCells){
    
    const classes = useStyles()

    const pages = [5,10,25]
    const [page, setPage] = useState(0);
    const[rowsPerPage, setRowsPerPage] = useState(pages[0])
    const TblContainer = props => (
        <Table className = {classes.table}>
            {props.children}
        </Table>
    )

    const handleChangePage = (event, newPage) =>{
        setPage(newPage)
    }

    const handleChangeRows = event =>{
        setRowsPerPage(parseInt(event.target.value,10))
    }

    const TblPagination = () => (<TablePagination
    rowsPerPageOptions = {pages}
    component = "div"
    rowsPerPage = {rowsPerPage}
    page = {page}
    count = "100"
    onChangePage={handleChangePage}
    onChangeRowsPerPage ={handleChangeRows}
    />)

    const recordsAfterPagingAndSorting = () => {
        return records.slice(page*rowsPerPage, (page+1)*rowsPerPage)
    }

    return {
        TblContainer,
        TblPagination,
        recordsAfterPagingAndSorting
    }

}