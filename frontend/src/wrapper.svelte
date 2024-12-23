<script lang="ts">
    const { connectButtonAction, connectButtonText, statusColor, statusText, favicon, children } = $props();
</script>

<svelte:head>
  <link rel="icon" type="image/svg" href="{favicon}?a=1"/>
  <title>WALL-E {statusText} - RoCCI e.V.</title>
</svelte:head>

<!-- Using Template by nauvalazhar (https://github.com/nauvalazhar/bootstrap-5-login-page) -->

<section class="h-100">
    <div class="container h-100">
        <div class="row justify-content-sm-center h-100">
            <div class="col-xxl-4 col-xl-5 col-lg-5 col-md-7 col-sm-9">
                <div class="text-center my-5">
                    <img src="/walle.png" alt="" width="100"><br>
                </div>
                <div class="card shadow-lg">
                    <div class="card-header py-3 border-0">
                        <div class="row">
                            <div class="col-sm-4 text-sm-start text-center mb-sm-0 mb-3">
                                <button onclick={connectButtonAction} class="btn btn-primary ms-auto">{connectButtonText}</button>
                            </div>
                            <div class="col-sm m-auto text-center">
                                Status: <strong class="{statusColor}">{statusText}</strong>
                            </div>
                        </div>
                    </div>
                    <div class="card-body p-5">
                        {@render children?.()}
                    </div>
                </div>
                <div class="text-center mt-5 text-muted">
                    Copyright &copy; 2025 <a href="https://rocci.net/impressum" target="_blank" class="text-reset">RoCCI e.V.</a> - All rights reserved
                </div>
            </div>
        </div>
    </div>
</section>