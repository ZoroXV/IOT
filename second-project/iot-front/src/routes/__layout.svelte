<script>
    import Header from '$lib/Header.svelte';
    import Footer from '$lib/Footer.svelte';
</script>

<div class="main_div">
    <div class="header">
        <Header/>
    </div>


    <div class="content">
        <slot></slot>
    </div>


    <div class="footer">
        <Footer/>
    </div>
</div>

<style>
    .main_div {
        position: absolute;
        top: 0px;
        bottom: 0px;
        right: 0px;
        left: 0px;
        height: 100%;
        background-color : #12161a;
  
        display: flex;
        flex-direction: column;
    }
  
    .header {
        background-color : #1d2228;   
        max-height: 150px;  
        flex-grow: 1;
    }

    .content {
        flex-grow: 20;

        display: flex;
        flex-direction: row;
    }
  
    .content {
        flex-grow: 6;
  
        display: flex;
        flex-direction: row;
        justify-content: center;
    }
  
    .footer {
        background-color : #1d2228;
        flex-grow: 1;
        max-height: 60px;
    }

  </style>